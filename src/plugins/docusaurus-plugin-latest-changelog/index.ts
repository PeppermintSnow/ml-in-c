import fs from 'fs';
import path from 'path';
import matter from 'gray-matter';
import semver from 'semver';

const CHANGELOG_PATH = path.resolve(__dirname, '../../../changelogs');

interface LatestChangelogData {
  version: string;
  description: string;
  date: string;
  url: string;
}

export default function(context: any, options: any) {
  return {
    name: 'docusaurus-plugin-latest-changelog',
    async loadContent() {
      try {
        const files = await fs.promises.readdir(CHANGELOG_PATH);
        const changelogFiles = files.filter((file: string) => /^v\d+\.\d+\.\d+/.test(file));
        const latestFile = changelogFiles.sort((a: string, b: string) => {
          return semver.rcompare(a, b);
        })[0];
        let latestFilePath = path.join(CHANGELOG_PATH, latestFile);
        if (!(latestFile.endsWith(".md") || latestFile.endsWith(".mdx"))) {
          const latestFileChildren = await fs.promises.readdir(latestFilePath);
          const indexFile = latestFileChildren.find((file: string) => /index\.(md|mdx)/.test(file));
          latestFilePath = path.join(latestFilePath, indexFile);
        }
        const fileContent = await fs.promises.readFile(latestFilePath, 'utf-8');

        const { data, content } = matter(fileContent);
        const fileName = latestFile.replace(/\.md$|\.mdx$/, "");
        const latestChangelog: LatestChangelogData = {
          version: fileName,
          description: data?.description || content.split("<!-- truncate -->")[0],
          date: data?.date.toISOString().slice(0, 10),
          url: `/changelogs/${fileName}`
        }

        return { latestChangelog: latestChangelog };
      } catch (error) {
        console.error('Error loading changelogs: ', error);
        return null;
      }
    },

    async contentLoaded({ content, actions }: any) {
      if (content && content.latestChangelog) {
        const { version, description, date, url } = content.latestChangelog;
        actions.setGlobalData({
          latestChangelog: {
            version,
            description,
            date,
            url
          }
        })
      }
    }
  }
}
