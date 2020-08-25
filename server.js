const express = require('express');
const app = express();
const user_name = require('bindings')('user_name')

app.get('/', function(req, res) {
    res.sendFile(__dirname +'/index.html');
});

app.get('/check', function(req, res) {
    let names = user_name.userNames();
    let uname = req.query.user;

    if (names.includes(uname)) {
        res.sendFile(__dirname +'/check_ok.html');
    } else {
        res.sendFile(__dirname +'/check_no.html');
    }
});

app.listen(3000);
