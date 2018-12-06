var https = require('https')
var fs = require('fs');

console.log(fs.existsSync('/home/owner/apps_rw/org.example.tizen-iotjs-audio/res/test.mp3'));

var fd = fs.openSync('/home/owner/apps_rw/org.example.tizen-iotjs-audio/res/test.mp3', 'r');

var stat = fs.fstatSync(fd);

console.log(stat);

var buffer = new Buffer(stat.size);
var bytesRead = fs.readSync(fd, buffer, 0, buffer.length, 0);
console.log(bytesRead);

var options = {
  method: 'POST',
  host: 'api.wit.ai',
  headers: {'Authorization': 'Bearer VZE6UQD4FZJQZZ65CJCSNMC23EGEJ7N7',
            'Content-Type': 'audio/mpeg3',
            'Content-length': bytesRead},
  path: '/speech?',
  rejectUnauthorized: false,
};

var request = https.request(options, function(response) {

  response.on('data', function(chunk) {
		console.log(chunk.toString());
  });

});
request.write(buffer);
request.end();
