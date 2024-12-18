#include <cassert>
#include <istream>
#include <ostream>

enum ListErrors {
	LISTERR_NULLPTR_INSERTION,
	LISTERR_EMPTY_EXTRACTION,
	LISTERR_NO_SUCH_ELEMENT,
};

#define TEMPLATE_T template <class T>

TEMPLATE_T class List {
public:
	List() : count_{0}, head_{nullptr} {} // Пустой конструктор

	List(int num, T * const ptr); // Конструктор из массива

	~List(); // Деструктор

	/*Ненужные методы*/
	List(List & src) = delete;
	void operator=(List & src) = delete;

	/*Число элементов в списке*/
	int size() const { return count_; }

	/*Вставка элемента в начало*/
	List & unshift(T const & el)
	{
		head_ = new Element{el, head_};
		++count_;
		return *this;
	}

	T & operator[](int const num);

	/*Извлечение начального элемента*/
	T shift();

private:
	int count_;

	struct Element {
		T data; /*Элемент, не указатель */
		Element * next;
		Element(T const & el, Element * newNext)
			: data{el}, /*В data будет копия el*/
			  next{newNext} {};
	} * head_; /*Голова списка*/

	/*Указатель на n-ый элемент списка, либо nullptr*/
	Element * NthElement_(int const n)
	{
		/*Возвращаемый указатель. Изначально указывает на голову */
		auto ret{head_};

		for (int i{0}; i < n; ++i){
			if (ret == nullptr)
				return nullptr;
			ret = ret->next;
		}
		return ret;
	}
};

TEMPLATE_T
T List<T>::shift()
{
	if (head_ == nullptr)
		throw LISTERR_EMPTY_EXTRACTION;

	Element * oldEl = head_; /*head_ не равен nullptr здесь*/
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
	if (ptr == nullptr)
		throw LISTERR_NULLPTR_INSERTION;
	
	for (auto i{num - 1}; i >= 0; --i)
		unshift(ptr[i]);
}

TEMPLATE_T
List<T>::~List()
{
	while (head_ != nullptr)
		shift();
}
	
TEMPLATE_T
T & List<T>::operator[](int const num) 
{
	if (num >= count_ || num < 0)
		throw LISTERR_NO_SUCH_ELEMENT;
	auto ptr {NthElement_(num)};
	assert(ptr != nullptr);
	return ptr->data;
}
