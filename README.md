# Todo List in C
Todo List using [mongoose](https://github.com/cesanta/mongoose/), [Backbone](https://github.com/jashkenas/backbone) and [SQLite3](http://sqlite.org/)

## Get Started
Dependencies are included as git submodules, you may need GNU Autotools to compile some dependencies.

To compile this app just run
```sh
./configure
make
```

## Deploy
You can deploy this to heroku using their buildpack for C applications. 

Just run the following commands:
```
heroku create --stack cedar --buildpack http://github.com/heroku/heroku-buildpack-c.git
git push heroku master
```

## Tests

### Integration
Integration tests are written entirely in ruby, using the rspec gem and the httparty gem to do http requests.

To run the integration tests you need tu run the app `./todo` then run `rspec` in another shell.
