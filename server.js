const express = require('express');
const app = express();
const user_name = require('bindings')('user_name')

app.get('/', function(req, res) {
    res.sendFile(__dirname +'/index.html');
});

app.get('/check', function(req, res) {
    let arr = user_name.userNames();
    let l = arr.length;
    let i = 0;
    let f = 0;
    let s = req.query.user;

    while (i < l) {
        if (arr[i].toUpperCase() == s.toUpperCase()) {
            f = 1;
            break;
        }
        i = i + 1;
    }

    if (f == 1) {
        res.sendFile(__dirname +'/check.html');
    } else {
        res.sendFile(__dirname +'/checkn.html');
    }
});

app.listen(3000);
