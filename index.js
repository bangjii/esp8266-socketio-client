const io = require('socket.io')
const server = io.listen(6666);

server.on('connection', function(socket){
  socket.on('message', function(msg){
    server.emit('message', msg);
    console.log(msg);
  });
});
