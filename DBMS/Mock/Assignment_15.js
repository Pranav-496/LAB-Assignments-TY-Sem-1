// Assignment 15: MongoDB aggregation and indexing
// Run with mongosh. This script uses its own database and resets its collection.
// The PDF's sample values use Book* field names, but its schema specifies article
// fields. The sample values below are mapped to the declared article schema.

db = db.getSiblingDB("dbms_assignment15_mock");
db.tech_articles.drop();
db.createCollection("tech_articles");

db.tech_articles.insertMany([
  {
    ArticleTitle: "Python Basics",
    ArticleSummary: "Introduction to Python",
    Writer: "Ananya",
    ArticleURL: "http://example.com/python1",
    Topics: ["Programming", "Python"],
    LikesCount: 120
  },
  {
    ArticleTitle: "Advanced Python",
    ArticleSummary: "Deep dive into Python",
    Writer: "Raj",
    ArticleURL: "http://example.com/python2",
    Topics: ["Programming", "Python"],
    LikesCount: 80
  },
  {
    ArticleTitle: "Java Fundamentals",
    ArticleSummary: "Basics of Java",
    Writer: "Sneha",
    ArticleURL: "http://example.com/java1",
    Topics: ["Programming", "Java"],
    LikesCount: 50
  },
  {
    ArticleTitle: "Web Development",
    ArticleSummary: "HTML, CSS, JS",
    Writer: "Ananya",
    ArticleURL: "http://example.com/web",
    Topics: ["Web", "HTML"],
    LikesCount: 30
  },
  {
    ArticleTitle: "Data Science Intro",
    ArticleSummary: "Getting started with Data Science",
    Writer: "Raj",
    ArticleURL: "http://example.com/ds",
    Topics: ["Data Science"],
    LikesCount: 200
  }
]);

// 1. Count the articles published by Ananya.
db.tech_articles.countDocuments({ Writer: "Ananya" });

// 2. Find Ananya's article with the fewest likes.
db.tech_articles
  .find({ Writer: "Ananya" })
  .sort({ LikesCount: 1, _id: 1 })
  .limit(1);

// Find Ananya's article with the most likes.
db.tech_articles
  .find({ Writer: "Ananya" })
  .sort({ LikesCount: -1, _id: 1 })
  .limit(1);

// 3. Calculate the average likes on Ananya's articles.
db.tech_articles.aggregate([
  { $match: { Writer: "Ananya" } },
  {
    $group: {
      _id: "$Writer",
      averageLikes: { $avg: "$LikesCount" }
    }
  }
]);

// 4. Find the first and last articles by Ananya, in insertion order.
db.tech_articles.aggregate([
  { $match: { Writer: "Ananya" } },
  { $sort: { _id: 1 } },
  {
    $group: {
      _id: "$Writer",
      firstArticle: { $first: "$$ROOT" },
      lastArticle: { $last: "$$ROOT" }
    }
  },
  { $project: { _id: 0, firstArticle: 1, lastArticle: 1 } }
]);

// 5. Index the declared writer field (the PDF refers to it as AuthorName).
db.tech_articles.createIndex({ Writer: 1 });

// Display Ananya's articles and inspect the query plan.
db.tech_articles.find({ Writer: "Ananya" });
db.tech_articles
  .find({ Writer: "Ananya" })
  .explain("executionStats");

// Force the index to confirm it is usable even if the small sample favors COLLSCAN.
db.tech_articles
  .find({ Writer: "Ananya" })
  .hint({ Writer: 1 })
  .explain("executionStats");
