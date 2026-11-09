// Assignment 13: MongoDB CRUD queries
// Run with mongosh. This script uses its own database and resets its collection.

db = db.getSiblingDB("dbms_assignment13_mock");
db.library_books.drop();
db.createCollection("library_books");

db.library_books.insertMany([
  {
    TITLE: "Python Basics",
    DESCRIPTION: "Introduction to Python",
    AUTHOR: "Ananya",
    LINK: "http://example.com/python1",
    CATEGORIES: ["Programming", "Python"],
    LIKES: 120
  },
  {
    TITLE: "Advanced Python",
    DESCRIPTION: "Deep dive into Python",
    AUTHOR: "Raj",
    LINK: "http://example.com/python2",
    CATEGORIES: ["Programming", "Python"],
    LIKES: 80
  },
  {
    TITLE: "Java Fundamentals",
    DESCRIPTION: "Basics of Java",
    AUTHOR: "Sneha",
    LINK: "http://example.com/java1",
    CATEGORIES: ["Programming", "Java"],
    LIKES: 50
  },
  {
    TITLE: "Web Development",
    DESCRIPTION: "HTML, CSS, JS",
    AUTHOR: "Ananya",
    LINK: "http://example.com/web",
    CATEGORIES: ["Web", "HTML"],
    LIKES: 30
  },
  {
    TITLE: "Data Science Intro",
    DESCRIPTION: "Getting started with Data Science",
    AUTHOR: "Raj",
    LINK: "http://example.com/ds",
    CATEGORIES: ["Data Science"],
    LIKES: 200
  }
]);

db.library_books.insertOne({
  TITLE: "Machine Learning",
  DESCRIPTION: "ML Concepts",
  AUTHOR: "Sneha",
  LINK: "http://example.com/ml",
  CATEGORIES: ["ML", "AI"],
  LIKES: 150,
  USERNAME: "user123",
  REVIEWS: ["Excellent", "Very helpful"]
});

// 1. Find the document titled "Python Basics".
db.library_books.find({ TITLE: "Python Basics" });

// 2. Find documents written by Ananya or titled "Python Basics".
db.library_books.find({
  $or: [{ AUTHOR: "Ananya" }, { TITLE: "Python Basics" }]
});

// 3. Find documents titled "Python Basics" and written by Ananya.
db.library_books.find({
  TITLE: "Python Basics",
  AUTHOR: "Ananya"
});

// 4. Find documents with more than 15 likes.
db.library_books.find({ LIKES: { $gt: 15 } });

// 5. Find documents with over 100 likes and either the title or author condition.
db.library_books.find({
  LIKES: { $gt: 100 },
  $or: [{ TITLE: "Python Basics" }, { AUTHOR: "Ananya" }]
});

// 6. Update the title of the "Python Basics" document.
db.library_books.updateOne(
  { TITLE: "Python Basics" },
  { $set: { TITLE: "Python Basics Overview" } }
);

// 7. Delete the document titled "JavaScriptIntro" (no match in the sample data).
db.library_books.deleteOne({ TITLE: "JavaScriptIntro" });

// 8. Display exactly two documents written by Ananya.
db.library_books.find({ AUTHOR: "Ananya" }).sort({ _id: 1 }).limit(2);

// 9. Display the second document published by Ananya, in insertion order.
db.library_books
  .find({ AUTHOR: "Ananya" })
  .skip(1)
  .limit(1);
