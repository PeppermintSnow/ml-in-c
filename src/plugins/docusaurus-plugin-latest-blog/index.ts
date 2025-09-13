import fs from 'fs';
import path from 'path';
import matter from 'gray-matter';

const BLOG_PATH = path.resolve(__dirname, '../../../blog');

interface LatestBlogPostData {
  title: string;
  metadata: Record<string, any>;
  content: string;
}

export default function(context: any, options: any) {
  return {
    name: 'docusaurus-plugin-latest-blog',
    async loadContent() {
      try {
        const files = await fs.promises.readdir(BLOG_PATH);
        const blogFiles = files.filter((file: string) => /^\d{4}-\d{2}-\d{2}-.*$/.test(file));
        const latestFile = blogFiles.sort((a: string, b: string) => {
          const aDate = new Date(a.split('-').slice(0, 3).join('-'));
          const bDate = new Date(b.split('-').slice(0, 3).join('-'));
          return bDate.getTime() - aDate.getTime();
        })[0];

        let latestFilePath = path.join(BLOG_PATH, latestFile);
        if (!(latestFile.endsWith(".md") || latestFile.endsWith(".mdx"))) {
          const latestFileChildren = await fs.promises.readdir(latestFilePath);
          const indexFile = latestFileChildren.find((file: string) => /index\.(md|mdx)/.test(file));
          latestFilePath = path.join(latestFilePath, indexFile);
        }
        const fileContent = await fs.promises.readFile(latestFilePath, 'utf-8');

        const { data, content } = matter(fileContent);
        const date = latestFile.split('-').slice(0, 3);
        const fileTitle = latestFile.split('-').slice(3);
        const latestBlogData: LatestBlogPostData = {
          title: data?.title || fileTitle.map(word => word.charAt(0).toUpperCase() + word.slice(1).join(' ')),
          description: data?.description || content.split("<!-- truncate -->")[0],
          date: date.join('-'),
          url: `/blog/${date.join('/')}/${fileTitle.join('-')}`
        }

        return { latestPost: latestBlogData };
      } catch (error) {
        console.error('Error loading blog posts: ', error);
        return null;
      }
    },

    async contentLoaded({ content, actions }: any) {
      if (content && content.latestPost) {
        const { title, description, date, url } = content.latestPost;
        actions.setGlobalData({
          latestBlogPost: {
            title,
            description,
            date,
            url
          }
        })
      }
    }
  }
}
