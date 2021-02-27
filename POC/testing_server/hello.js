const http = require("http");
const host = 'localhost';
const port = 8000;

let a = 1.0;
let b = 1.0;

const requestListener = function (req, res) {
    res.writeHead(200);
    a+=0.2;
    b+=0.4;

    res.end(Math.sin(a).toFixed(8).toString()+","+Math.sin(b).toFixed(8).toString());
};

const server = http.createServer(requestListener);
server.listen(port, host, () => {
    console.log(`Server is running on http://${host}:${port}`);
});
