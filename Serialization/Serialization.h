#pragma once
#include <vector>
#include <array>
#include <iostream>
#include <memory>

class Stream
{
public:
	Stream() {}

	template<typename T>
	void write(const T& data)
	{
		const auto lastElem = buf.size();
		buf.resize(buf.size() + sizeof(data));
		memcpy((char*)(buf.data() + lastElem), (char*)&data, sizeof(data));
	}

	template<typename T>
	void write(T* data)
	{
		const auto lastElem = buf.size();
		buf.resize(buf.size() + sizeof(std::decay_t<decltype(*data)>));
		memcpy((char*)(buf.data() + lastElem), (char*)data, sizeof(std::decay_t<decltype(*data)>));
	}

	template<typename T, size_t N>
	void write(const T(&arr)[N])
	{
		const auto lastElem = buf.size();
		buf.resize(buf.size() + sizeof(T)*N);
		memcpy((char*)(buf.data() + lastElem), (char*)arr, sizeof(T) * N);
	}

	template<typename T>
	T read()
	{
		T res;
		memcpy((char*)&res, buf.data() + buf.size() - sizeof(T), sizeof(T));
		buf.erase(buf.begin() + buf.size() - sizeof(T), buf.begin() + buf.size());
		return res;
	}

	template<typename T>
	requires std::is_pointer_v<T>
	auto read()
	{
		using decayed = std::decay_t<decltype(*T())>;
		std::unique_ptr<decayed> res(new(decayed));
		memcpy((char*)res.get(), buf.data() + buf.size() - sizeof(decayed), sizeof(decayed));
		buf.erase(buf.begin() + buf.size() - sizeof(decayed), buf.begin() + buf.size());
		return res;
	}

	template<typename T, size_t N>
    auto read()
	{
		std::array<T, N> res;
		char* ptr = (char*)(buf.data() + buf.size() - N * sizeof(T));
		memcpy((char*)res.data(), ptr, N * sizeof(T));
		buf.erase(buf.begin() + buf.size() - N * sizeof(T), buf.begin() + buf.size());
		return res;
	}

private:
	std::vector<char> buf;
};