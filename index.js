const express = require('express');
const fs = require('fs');
const path = require('path');

const app = express();

// Path to your files folder
const FILES_DIR = path.join(__dirname, 'files');

// Helper to validate slugs
const SLUG_RE = /^[A-Za-z0-9_-]+$/;

app.get('/:slug', (req, res) => {
  const slug = req.params.slug;

  if (!SLUG_RE.test(slug)) {
    return res.status(400).send('Invalid slug.');
  }

  const filePath = path.join(FILES_DIR, slug + '.c');

  fs.readFile(filePath, 'utf8', (err, data) => {
    if (err) {
      if (err.code === 'ENOENT') {
        return res.status(404).send('File not found.');
      }
      return res.status(500).send('Server error.');
    }

    // Set text/plain so browser shows raw text
    res.type('text/plain').send(data);
  });
});

// Optional: root route
app.get('/', (req, res) => {
  res.send('Use /<slug> to view a file. Example: /shift-reduce');
});

// Start server
const PORT = process.env.PORT || 3000;
app.listen(PORT, () => console.log(`Server running on port ${PORT}`));
