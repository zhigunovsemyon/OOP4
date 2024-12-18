#include <cstddef>
#include <istream>
#include <ostream>

#define TEMPLATE_T template <class T>

TEMPLATE_T class List {
public:
	List() : count_{0}, head_{nullptr} {} // Пустой конструктор

	List(int num, T * const ptr); // Конструктор из массива

	~List(); // Деструктор

	std::size_t size() { return count_; }

	List & unshift(T const & el)
	{
		head_ = new Element{el, head_};
		++count_;
		return *this;
	}

	T shift();

private:
	std::size_t count_;

	struct Element {
		T data; /*Элемент, не указатель */
		Element * next;
		Element(T const & el, Element * newNext)
			: data{el}, /*В data будет копия el*/
			  next{newNext} {};
	} * head_;
};

TEMPLATE_T
T List<T>::shift()
{
	Element * oldEl = head_; /*!ПОТЕНЦИАЛЬНОЕ РАЗИМЕНОВАНИЕ NULL!*/
	/*Копирование данных из элемента списка на стек функции*/
	T ret = oldEl->data;
	head_ = oldEl->next;
	delete oldEl;
	--count_; /*Уменьшение счётчика элементов*/
	return ret;
}

TEMPLATE_T
List<T>::List(int num, T * const ptr) : count_{0}, head_{nullptr}
{
	for (auto i{num - 1}; i >= 0; --i)
		unshift(ptr[i]);
}

TEMPLATE_T
List<T>::~List()
{
	while (head_ != nullptr)
		shift();
}
