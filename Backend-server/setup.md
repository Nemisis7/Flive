# Setting up the backend server.

### Prerequisites:
```
- nodejs
- express
- connect
- http
- social-counter
- body-parser
```

### Installing node.js

```
Linux based distributions
  sudo apt-get install build-essential curl git m4 ruby texinfo libbz2-dev libcurl4-openssl-dev libexpat-dev libncurses-dev zlib1g-dev

Windows based distributions:

  https://nodejs.org/en/download/
  
Or:

  sudo su
  apt-get -y update
  apt-get install git
  curl -sL https://deb.nodesource.com/setup_6.x | sudo -E bash -  
  apt-get install -y nodejs  

Mac based distributions:
  ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
  brew install node
```

You may check if node.js is installed by running this command;
```bash
npm -v
```

### Installing the required libraries

```bash
npm install express
npm install connect
npm install http
npm install social-counter
npm install body-parser
```


### Installing apache - linux based distributions: 

Install apache:
```bash
sudo apt-get update
sudo apt-get install apache2
```

CD to the relevent directory

```
cd var/www/html/
```

### Starting the server (all distributions)

Create the file, in this case name it app.js, paste in the following code:

```js
var connect = require('connect'); // requires the connect module
var http = require('http'); // requires the http module
var app = connect(); // call the function connect, that was previously defined by calling the module connect
var currenttwitername = "realDonaldTrump" // defines the variable "currenttwittername" to the scope memory
var socialCounter = require('social-counter'), // requires the social-counter module
	socialCounterPromise; // defines the variable "socialCounterPromise" to the scope memory
var bodyParser = require('body-parser'); // requires the body-parser module

app.use(bodyParser.urlencoded({ // utilizes the method "use" of "app", extends urlenocded function as a method of previously defined bodyParser
	extended: false // sets extended to false - the "extended" syntax allows for rich objects and arrays to be encoded into the URL-encoded format, allowing for a JSON-like experience with URL-encoded.
}));

getFollowers = function(res, userName) { // defines the function getFollowers
	userName = currenttwitername; // Sets a required argument of the function getFollowers to "currenttwitternam"
	socialCounterPromise = socialCounter.init({ // calls init a method of socialCounter
		'twitter': userName // init takes one argument, a table, sets the first key [0] to userName which was a required argument
	});
	socialCounterPromise.then(function() { // promise yall
		var twitterNumber = socialCounter.getTwitter() // getTwiiter() function returns the number of followers of the twitter account defined in the init method of soialConter
    _return = "@" + userName + " " + twitterNumber
		console.log(_return) // logs to the output for debug 
		res.end(_return) // res.end returns this to the body, in the format @<USERNAME>_Followers:<SPACE><#TWITTER_FOLLOWERS>
	});
}

setFollowers = function(res, userName) { // defines the function getFollowers, takes two arguments
	currenttwitername = userName // sets the variable currenttwittername, defined in global scope to username
	res.end("SET: " + currenttwitername) // returns to the body "SET:<SPACE><CURRENT_TWITTER_NAME>"
}

app.use(function(req, res) { // utilizes the method "use" of app, the argument being a function the first the request, this being the trailing url query split at -
	var fields = req._parsedUrl.query.split('-'); // splits the trailing url query at -
	if (fields[0] == "GET") { // if the first key of fields (split url at - and then pushed into table) is equal to GET
		getFollowers(res, fields[1]) // call getFollowers function, the first being a refrence to the body,the second argument being the second key of the array fields
	} else if (fields[0] == "SET") { // elseif the first key of fields (split url at - and then pushed into table) is equal to SET
		setFollowers(res, fields[1]) // calls the function SET, this sets the currenttwittername to the second key of the table fields
	}
});

http.createServer(app).listen(3000); // sets the app to run on port 3000
```
You may run the file by executing in the bash:
```bash
node app.js
```

If you're using a VPS, you can install pm2, this may be done by executing this in the linux bash
```bash
sudo npm install pm2 -g
```

You'll now be able to run the application with increased metrics, error logging in its own indefinite productions log:
```bash
pm2 start app.js
```

You can then monitor the apps usage by executing

```bash
pm2 monit app```
