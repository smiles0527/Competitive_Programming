window.EDITORIAL_SITE_CONFIG = {
  collections: [
    {
      id: "cses",
      label: "CSES",
      path: "../CSES",
      repositoryPath: "CSES",
      defaultSection: "introductory",
      sections: [
        ["introductory", "Introductory Problems"],
        ["Slidingwindow", "Sliding Window Problems"],
        ["Bitwise", "Bitwise Operations"]
      ]
    }
  ],
  editor: {
    apiBase: "https://REPLACE-WITH-YOUR-WORKER.workers.dev"
  }
};
