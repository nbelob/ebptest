const user_name = require('bindings')('user_name')

//console.log(user_name.userNames());

var l;
var i;
var arr = user_name.userNames();

l = arr.length;

/*
user_name.userNames().forEach(sss =>
{
    console.log(sss)
}
)
*/

i = 0;
f = 0;
while (i < l) {
    console.log(arr[i]);
    /*
    if (arr[i].toUpperCase() == 'АдмиНИстратор'.toUpperCase()) {
        f = 1;
        break;
    }
    */
    i = i + 1;
}
console.log(f);
