interface LatestBlogPostProps {
  title: string;
  content: string;
}

const LatestBlogPost: React.FC<LatestBlogPostProps> = ({ title, content }) => {
  return (
    <div>
      {title}
    </div>
  )
}

export default LatestBlogPost;
