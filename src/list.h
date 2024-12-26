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

	/*Получение num элемента списка. Поддерживается индексация с конца*/
	T & operator[](int num);

	T & first() { return operator[](0); }

	T & last() { return operator[](-1); }

	/*Извлечение начального элемента*/
	T shift();

	/*Извлечение последнего элемента*/
	T pop() { return pull(-1); }

	/*Вставка элемента в конец*/
	List & push(T const & el)
	{
		return (head_ == nullptr) ? unshift(el) : insert(-1, el);
	}

	/*Вставка после некотого элемента*/
	List & insert(int, T const &);

	/*Извлечение элемента под некоторым индексом*/
	T pull(int);

	/*Вывод списка элементов в объект ostream*/
	List & print(std::ostream &);

	friend std::ostream & operator<<(std::ostream & ost, List & l)
	{
		l.print(ost);
		return ost;
	}

	/*Наполнение списка из стандартного потока*/
	List & read(std::istream & ist)
	{
		do {
			T temp;	
			ist >> temp;
			if(ist.fail())
				break;
			/*else*/
			push(temp);
		} while(true);

		/*Возврат ссылки на список для построения цепи*/
		return *this;
	}

private:
	int count_;

	struct Element {
		T data; /*Элемент, не указатель */
		Element * next;
		/*Конструктор*/
		Element(T const & el, Element * newNext)
			: data{el}, /*В data будет копия el*/
			  next{newNext} {};
	} * head_; /*Голова списка*/

	/*Указатель на n-ый элемент списка, либо nullptr*/
	Element * NthElement_(int const n)
	{
		assert(n >= 0); // До сюда не должен доходить индекс < 0
		/*Возвращаемый указатель. Изначально указывает на голову */
		auto ret{head_};

		for (int i{0}; i < n; ++i) {
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
T & List<T>::operator[](int num)
{
	/*Перестановка индекса в конец*/
	if (num < 0)
		num += count_;

	if (num >= count_ || num < 0)
		throw LISTERR_NO_SUCH_ELEMENT;
	auto ptr{NthElement_(num)};
	assert(ptr != nullptr);
	return ptr->data;
}

TEMPLATE_T T List<T>::pull(int num)
{
	if (count_ == 0)
		throw LISTERR_EMPTY_EXTRACTION;

	if (num < 0)
		num += count_;
	if (num >= count_ || num < 0)
		throw LISTERR_NO_SUCH_ELEMENT;
	if (num == 0)
		return std::move(shift());

	/*Указатель на предпоследний элемент,
	 *в котором будет заменён next*/
	auto ptr{NthElement_(count_ - 2)};
	assert(ptr->next != nullptr);

	T ret = ptr->next->data;
	ptr->next = ptr->next->next;
	delete ptr->next;
	--count_;
	return ret;
}

/*Метод вставки после некоторого индекса*/
TEMPLATE_T List<T> & List<T>::insert(int num, T const & el)
{
	if (num < 0)
		num += count_;
	if (num >= count_ || num < 0)
		throw LISTERR_NO_SUCH_ELEMENT;

	/*Указатель на последний элемент*/
	auto ptr{NthElement_(num)};
	assert(ptr != nullptr);

	ptr->next = new Element{el, ptr->next};
	++count_;
	return *this;
}

TEMPLATE_T
List<T> & List<T>::print(std::ostream & ost)
{
	int i{0};
	/* Цикл с критерия окончания внутри. Если список пустой (count_ == 0),
	цикл не начинается */
	while (count_) {
		ost << operator[](i++);
		if (i >= count_)
			break;
		ost << '\n';
	}
	return *this;
}
