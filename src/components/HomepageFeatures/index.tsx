import type {ReactNode} from 'react';
import Link from '@docusaurus/Link';
import clsx from 'clsx';
import Heading from '@theme/Heading';
import styles from './styles.module.css';
import useGlobalData, {usePluginData} from '@docusaurus/useGlobalData';
import Markdown from 'react-markdown';
import rehypeKatex from 'rehype-katex';
import remarkMath from 'remark-math';

function Feature({title, Svg, description}: FeatureItem) {
  return (
    <div className={clsx('col col--4')}>
      <div className="text--center">
        <Svg className={styles.featureSvg} role="img" />
      </div>
      <div className="text--center padding-horiz--md">
        <Heading as="h3">{title}</Heading>
        <p>{description}</p>
      </div>
    </div>
  );
}

function LatestBlogPost() {
  const { title, date, description, url } = usePluginData('docusaurus-plugin-latest-blog')['latestBlogPost'];
  return (
    <div className="card latest-blog">
      <div className="card__header">
        <h2>
          <Link to={url} className="homepage__card__header">Latest Blog Post</Link>
        </h2>
        <h3 className="latest-blog__title">{title}</h3>
        <h4 className="latest-blog__date">{date}</h4>
      </div>
      <div className="card__body latest-blog__body">
        <p className="latest-blog__description">
          <Markdown
            remarkPlugins={[remarkMath]}
            rehypePlugins={[rehypeKatex]}
          >
            {description}
          </Markdown>
        </p>
      </div>
      <div className="latest-blog__button">
        <Link className="button hero__button button--block">Read more</Link>
      </div>
    </div>
  );
}

function LatestChangelog() {
  const pluginData = usePluginData('docusaurus-plugin-latest-changelog');
  console.log(useGlobalData())
  if (!pluginData) {
    return <p>Loading</p>
  }
  const { version, description, date, url } = pluginData.latestChangelog;
  return (
    <div className="card latest-blog">
      <div className="card__header">
        <h2>
          <Link to={url} className="homepage__card__header">Latest Changes</Link>
        </h2>
        <h3 className="latest-blog__title">{version}</h3>
        <h4 className="latest-blog__date">{date}</h4>
      </div>
      <div className="card__body latest-blog__body">
        <p className="latest-blog__description">
          <Markdown
            remarkPlugins={[remarkMath]}
            rehypePlugins={[rehypeKatex]}
          >
            {description}
          </Markdown>
        </p>
      </div>
      <div className="latest-blog__button">
        <Link className="button hero__button button--block">Read more</Link>
      </div>
    </div>
  )

}

export default function HomepageFeatures(): ReactNode {
  return (
    <section className={styles.features}>
      <div className="container">
        <div className="row homepage__row">
          <div className="col">
            <LatestBlogPost />
          </div>
          <div className="col">
            <LatestChangelog />
          </div>
        </div>
        <div className="row homepage__row">
        </div>
      </div>
    </section>
  );
}
