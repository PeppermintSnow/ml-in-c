import React, {type ReactNode} from 'react';
import BlogPostItem from '@theme-original/BlogPostItem';
import type BlogPostItemType from '@theme/BlogPostItem';
import type {WrapperProps} from '@docusaurus/types';
import GiscusComponent from '@site/src/components/GiscusComponent';
import { useBlogPost } from '@docusaurus/plugin-content-blog/client';
import useIsBrowser from '@docusaurus/useIsBrowser'

type Props = WrapperProps<typeof BlogPostItemType>;

export default function BlogPostItemWrapper(props: Props): ReactNode {
  const { metadata, isBlogPostPage } = useBlogPost();
  const enableComment = metadata?.["permalink"].split("/")[2] === "blog"
  const isBrowser = useIsBrowser();
  return (
    <>
      <BlogPostItem {...props} />
      {(enableComment && isBlogPostPage) && (
        <>
          <div>&nbsp;</div>
          <GiscusComponent />
        </>
      )}
    </>
  );
}
