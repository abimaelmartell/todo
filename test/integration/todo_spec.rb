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

def put url, options
  HTTParty.put BASE_URL + url, options
end

def delete url
  HTTParty.delete BASE_URL + url
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
      todos_count = get('/todos').count
      post '/todos', body: { text: 'buy some milk' }.to_json
      new_todos_count = get('/todos').count
      new_todos_count.should be > todos_count
    end

    it 'should return created todo json' do
      todo = { text: 'testing this thing :)' }
      todo_json = post '/todos', body: todo.to_json
      todo_json['text'].should eq(todo[:text])
    end
  end

  describe 'PUT /todos/[:id]' do
    it 'should update an existing todo' do
      todo = post '/todos', body: { text: 'this is an existing todo' }.to_json

      updated = put "/todos/#{todo['id']}", body: { text: 'new text', status: 1 }.to_json

      updated['status'].should eq(1)
      updated['text'].should eq('new text')
    end
  end

  describe 'DELETE /todos/[:id]' do
    it 'should delete an existing todo' do
      todo = post '/todos', body: { text: 'this is an existing todo' }.to_json

      delete "/todos/#{todo['id']}"

      res = get "/todos/#{todo['id']}"
      res.code.should eq(404)
    end
  end

  describe 'GET /todos/[:id]' do
    it 'should render an existing todo' do
      todo = post '/todos', body: { text: 'this is an existing todo' }.to_json
      
      res = get "/todos/#{todo['id']}"

      res.code.should eq(200)
      res.content_type.should eq('application/json')
      res['text'].should eq('this is an existing todo')
    end
  end
end
