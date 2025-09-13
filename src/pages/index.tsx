import type {ReactNode} from 'react';
import clsx from 'clsx';
import Link from '@docusaurus/Link';
import useDocusaurusContext from '@docusaurus/useDocusaurusContext';
import Layout from '@theme/Layout';
import HomepageFeatures from '@site/src/components/HomepageFeatures';
import Heading from '@theme/Heading';

import styles from './index.module.css';

function HomepageHeader() {
  const {siteConfig} = useDocusaurusContext();
  return (
    <header className="hero hero--primary hero__banner">
      <div className="container">
        <div className="row">
          <div className="col col--6">
            <Heading as="h1" className="hero__title">
              ML-in-C
            </Heading>
            <p className="hero__subtitle">
              An experimental dive into machine learning – built specifically for personal studies
            </p>
            <div className={styles.buttons}>
              <Link
                className="button hero__button button--lg"
                to="/docs/wip">
                Getting Started
              </Link>
              <Link
                className="button hero__button button--lg"
                to="/api/wip">
                API Reference
              </Link>
            </div>
          </div>
          <div className="col col--6">
            <ul className="hero__features">
              <li>Comprehensive development logs to track progress and enhance learning.</li>
              <li>Rebuilt from scratch to deepen understanding and reinforce knowledge.</li>
              <li>No external dependencies—pure C to keep things educational.</li>
              <li>Open source—freely explore and learn as development progresses.</li>
            </ul>
          </div>
        </div>
      </div>
    </header>
  );
}

export default function Home(): ReactNode {
  const {siteConfig} = useDocusaurusContext();
  return (
    <Layout
      title={`${siteConfig.title}`}
      description="Description will go into a meta tag in <head />">
      <HomepageHeader />
      <main>
        <HomepageFeatures />
      </main>
    </Layout>
  );
}
