require 'net/http'
require 'json'
require 'httparty'

BASE_URL = 'http://localhost:3000'

def get url
 HTTParty.get BASE_URL + url
end

def post url, options
  HTTParty.post BASE_URL + url, options
end

describe 'Integration' do
  describe 'GET /' do
    it 'returns successful response' do
      get('/').code.should eq(200)
    end

    it 'renders /public/index.html' do
      get('/').body.should eq(File.read('public/index.html'))
    end
  end

  describe 'GET /todos' do
    it 'should return json content type' do
      get('/todos').content_type.should eq('application/json')
    end

    it 'should return a valid json string' do
      expect{ JSON.parse get('/todos').body }.to_not raise_error
    end
  end

  describe 'POST /todos' do
    it 'should create a new todo' do
      todos_count = JSON.parse(get('/todos').body).count
      post '/todos', body: { text: 'buy some milk' }.to_json
      new_todos_count = JSON.parse(get('/todos').body).count
      new_todos_count.should be > todos_count
    end

    it 'should return created todo json' do
      todo = { text: 'testing this thing :)' }
      res = post '/todos', body: todo.to_json
      todo_json = JSON.parse(res.body)
      todo_json['text'].should eq(todo[:text])
    end
  end
end
