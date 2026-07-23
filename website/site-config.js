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
        ["Bitwise", "Bitwise Operations"],
        ["Graphs", "Graph Algorithms"],
        ["DP", "Dynamic Programming"],
        ["Sorting", "Sorting and Searching"],
        ["Interactive", "Interactive Problems"],
      ],
    },
  ],
  editor: {
    apiBase: "https://editorial-editor-gateway.smilescp.workers.dev",
    localApiBase: "http://127.0.0.1:8787",
  },
};
