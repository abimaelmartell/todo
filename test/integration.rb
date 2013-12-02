require 'net/http'

BASE_URL = 'http://localhost:3000'

def get url
  Net::HTTP.get_response URI(BASE_URL + url)
end

describe 'Integration' do
  describe 'GET /' do
    it 'returns successful response' do
      get('/').code.should eq('200')
    end

    it 'renders /public/index.html' do
      get('/').body.should eq(File.read('public/index.html'))
    end
  end

  describe 'GET /todos' do
    it 'should return json content type' do
      get('/todos').content_type.should eq('application/json')
    end
  end
end
