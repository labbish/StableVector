#pragma once

#include <forward_list>
#include <iterator>

namespace labbish {
	template <typename T>
	class StableVector :public std::forward_list<T> {
	public:
		inline StableVector() = default;
		inline StableVector(const std::initializer_list<T>& init) :std::forward_list<T>() {
			auto it = this->before_begin();
			for (const T& value : init) {
				it = this->insert_after(it, value);
			}
		}
		inline size_t size() const {
			return std::distance(this->begin(), this->end());
		}
		inline T& operator[](size_t index) {
			auto it = this->begin();
			size_t currentIndex = 0;
			while (it != this->end()) {
				if (currentIndex == index) {
					return *it;
				}
				++it;
				++currentIndex;
			}
			throw std::out_of_range(std::format("StableVector index out of range: {}", index));
		}
		inline const T& operator[](size_t index) const {
			auto it = this->begin();
			size_t currentIndex = 0;
			while (it != this->end()) {
				if (currentIndex == index) {
					return *it;
				}
				++it;
				++currentIndex;
			}
			throw std::out_of_range(std::format("StableVector index out of range: {}", index));
		}
		inline void push_back(const T& value) {
			if (this->empty()) {
				this->push_front(value);
				return;
			}
			auto it = this->begin();
			while (std::next(it) != this->end()) {
				++it;
			}
			this->insert_after(it, value);
		}
		inline void pop_back() {
			if (this->empty()) {
				throw std::out_of_range("StableVector is empty");
			}
			if (this->size() == 1) {
				this->pop_front();
				return;
			}
			auto it = this->begin();
			while (std::next(it) != this->end() && std::next(std::next(it)) != this->end()) {
				++it;
			}
			this->erase_after(it);
		}
		inline void erase(size_t index) {
			if (index >= this->size()) {
				throw std::out_of_range(std::format("StableVector index out of range: {}", index));
			}
			if (index == 0) {
				this->pop_front();
				return;
			}
			auto it = this->begin();
			size_t currentIndex = 0;
			while (currentIndex < index - 1) {
				++it;
				++currentIndex;
			}
			this->erase_after(it);
		}
		inline void insert(size_t index, const T& value) {
			if (index > this->size()) {
				throw std::out_of_range(std::format("StableVector index out of range: {}", index));
			}
			if (index == 0) {
				this->push_front(value);
				return;
			}
			auto it = this->begin();
			size_t currentIndex = 0;
			while (currentIndex < index - 1) {
				++it;
				++currentIndex;
			}
			this->insert_after(it, value);
		}
	};
}
