const http = require("http");
const host = 'localhost';
const port = 8000;

let a = 100;
let b = 12;

const requestListener = function (req, res) {
    res.writeHead(200);
    a+=1;
    b+=2;
    res.end(a.toString()+","+b.toString());
};

const server = http.createServer(requestListener);
server.listen(port, host, () => {
    console.log(`Server is running on http://${host}:${port}`);
});