#include "../headers/Menu.h"

// Constructor
Menu::Menu(std::string fontName, int fontSize = 40,  int left = 0, int top = 0, int width = 0, int height = 0, bool isSelectable = false) :fontSize(fontSize), selectedItemIndex(0), size({ width, height }), padding({left, top}) {
	if (!font.loadFromFile("./fonts/" + fontName + ".ttf")) return;
	if (!isSelectable) setSelectedItemIndex(-1);
};

// Destructor
Menu::~Menu() {};

void Menu::addNewItem(std::string name, std::function<void()> callback = [](){}) {
	menuFunctions[name] = callback;
	sf::Text item;
	item.setFont(font);
	item.setFillColor((menu.size() == selectedItemIndex) ? sf::Color::Red: sf::Color::White);
	item.setString(name);
	item.setCharacterSize(fontSize);
	item.setPosition(sf::Vector2f((size.width / 4) + padding.left, ((size.height / 4) * menu.size()) + padding.top));
	menu.push_back(item);
};

void Menu::draw(sf::RenderWindow &window) {
	for (unsigned int i = 0; i < menu.size(); i++) window.draw(menu[i]);
};

void Menu::runSelected() {
	menuFunctions[menu[selectedItemIndex].getString()]();
};

void Menu::move(MenuDirections dir) {
	switch (dir) {
	case MenuDirections::UP:
		if (selectedItemIndex - 1 >= 0) {
			menu[selectedItemIndex].setFillColor(sf::Color::White);
			selectedItemIndex--;
			menu[selectedItemIndex].setFillColor(sf::Color::Red);
		}
		break;
	case MenuDirections::DOWN:
		if (selectedItemIndex + 1 < menu.size()) {
			menu[selectedItemIndex].setFillColor(sf::Color::White);
			selectedItemIndex++;
			menu[selectedItemIndex].setFillColor(sf::Color::Red);
		}
		break;
	default:
		break;
	}
};

void Menu::handleEvents(sf::Event event) {
	switch (event.key.code) {
	case sf::Keyboard::Enter:
		runSelected();
		break;
	case sf::Keyboard::Up:
		move(MenuDirections::UP);
		break;
	case sf::Keyboard::Down:
		move(MenuDirections::DOWN);
		break;
	default:
		break;
	}
};

void Menu::updateItem(int index, std::string text) {
	menu[index].setString(text);
};

void Menu::setSelectedItemIndex(int index) {
	selectedItemIndex = index;
};