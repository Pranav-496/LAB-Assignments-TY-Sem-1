// Assignment 14: MongoDB CRUD queries
// Run with mongosh. This script uses its own database and resets its collection.

db = db.getSiblingDB("dbms_assignment14_mock");
db.library_books.drop();
db.createCollection("library_books");

db.library_books.insertMany([
  {
    TITLE: "JavaScript Essentials",
    DESCRIPTION: "Learn JS basics",
    AUTHOR: "Meera",
    LINK: "http://example.com/js1",
    CATEGORIES: ["Programming", "JavaScript"],
    LIKES: 90
  },
  {
    TITLE: "NodeJS Guide",
    DESCRIPTION: "Server-side JS",
    AUTHOR: "Ananya",
    LINK: "http://example.com/node",
    CATEGORIES: ["Programming", "NodeJS"],
    LIKES: 40
  },
  {
    TITLE: "ReactJS Intro",
    DESCRIPTION: "Frontend framework",
    AUTHOR: "Raj",
    LINK: "http://example.com/react",
    CATEGORIES: ["Web", "ReactJS"],
    LIKES: 110
  },
  {
    TITLE: "Python for Data Analysis",
    DESCRIPTION: "Data analysis using Python",
    AUTHOR: "Sneha",
    LINK: "http://example.com/python_data",
    CATEGORIES: ["Python", "Data"],
    LIKES: 75
  },
  {
    TITLE: "AI Basics",
    DESCRIPTION: "Introduction to AI",
    AUTHOR: "Meera",
    LINK: "http://example.com/ai",
    CATEGORIES: ["AI", "ML"],
    LIKES: 60
  }
]);

db.library_books.insertOne({
  TITLE: "Deep Learning",
  DESCRIPTION: "Neural networks",
  AUTHOR: "Raj",
  LINK: "http://example.com/dl",
  CATEGORIES: ["AI", "DeepLearning"],
  LIKES: 130,
  USERNAME: "user456",
  REVIEWS: ["Very informative", "Excellent guide"]
});

// 1. Find the document titled "ReactJS Intro".
db.library_books.find({ TITLE: "ReactJS Intro" });

// 2. Find documents written by Ananya or titled "ReactJS Intro".
db.library_books.find({
  $or: [{ AUTHOR: "Ananya" }, { TITLE: "ReactJS Intro" }]
});

// 3. Find documents titled "ReactJS Intro" and written by Ananya (no match).
db.library_books.find({
  TITLE: "ReactJS Intro",
  AUTHOR: "Ananya"
});

// 4. Find documents with more than 100 likes.
db.library_books.find({ LIKES: { $gt: 100 } });

// 5. Find documents with over 100 likes and either the title or author condition.
db.library_books.find({
  LIKES: { $gt: 100 },
  $or: [{ TITLE: "ReactJS Intro" }, { AUTHOR: "Raj" }]
});

// 6. Display exactly two documents written by Meera.
db.library_books.find({ AUTHOR: "Meera" }).sort({ _id: 1 }).limit(2);

// 7. Display the second document published by Meera, in insertion order.
db.library_books
  .find({ AUTHOR: "Meera" })
  .sort({ _id: 1 })
  .skip(1)
  .limit(1);

// 8. Update the title of the "ReactJS Intro" document.
db.library_books.updateOne(
  { TITLE: "ReactJS Intro" },
  { $set: { TITLE: "ReactJS Overview" } }
);

// 9. Delete the document titled "AI Basics".
// Keep this after the Meera queries so both seeded Meera documents are available.
db.library_books.deleteOne({ TITLE: "AI Basics" });
