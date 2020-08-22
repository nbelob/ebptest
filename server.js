const express = require('express');
const app = express();

app.get('/', function(req, res) {
    res.sendFile(__dirname +'/index.html');
});

app.get('/check', function(req, res) {
    if (req.query.user === 'Администратор') {
        res.sendFile(__dirname +'/check.html');
    } else {
        res.sendFile(__dirname +'/checkn.html');
    }
});

app.listen(3000);
