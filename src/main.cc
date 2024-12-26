/*
 Разработать шаблон структуры данных в памяти. Тип хранимого элемента - параметр
 шаблона. Шаблон содержит объект. Реализовать:
	+операции включения/удаления по заданному логическому номеру,
	загрузки хранимых элементов в структуру данных из stdin.
 Проверить работу шаблона на разработанном классе, используя его как
 параметр шаблона. Структура данных: односвязный список, элемент списка хранит
 непосредственно объект.
 */
#include "list.h"
#include "matr.h"
#include <iostream>
#include <vector>

int main()
{
	try {
		std::vector<Matrix> ms {{2}, {3}};
		List<Matrix> l{ (int)ms.size(), ms.data() };
		std::cout << l << '\n';
		std::cin >> l.erase();
		std::cout << "l:\n"<< l << '\n';
		return 0;
	} catch (ListErrors le) {
		switch (le) {
		case LISTERR_NULLPTR_INSERTION:
			std::cerr << "Некорректный массив!\n";
			return EXIT_FAILURE;
		case LISTERR_EMPTY_EXTRACTION:
			std::cerr << "Извлечение из пустого массива!\n";
			return EXIT_FAILURE;
		case LISTERR_NO_SUCH_ELEMENT:
			std::cerr << "Неправильно указан индекс!\n";
			return EXIT_FAILURE;
		}
	}
}
