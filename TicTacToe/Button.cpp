#include "Button.h"

Button::Button(sf::Texture* texture, sf::Vector2f position) {
	this->button_t = *texture;
	this->button.setTexture(*texture);
	this->setPosition(position);
}

Button::~Button() {}

//		MODIFIERS
void Button::setPosition(sf::Vector2f position, bool fromCenter) {
	if (!fromCenter)
		button.setPosition(position);
	else
		button.setPosition(position.x - button.getGlobalBounds().width / 2, position.y - button.getGlobalBounds().height / 2);
}

void Button::setScale(float targetX, float targetY) {
	button.setScale(targetX / button.getGlobalBounds().width,
		targetY / button.getGlobalBounds().height);
}


//		ACCESSORS
const bool Button::isPressed() const
{
	if (this->buttonState == BTN_ACTIVE)
		return true;

	return false;
}

const sf::FloatRect Button::getGlobalBounds() const
{
	return button.getGlobalBounds();
}

//		FUNCTIONS
void Button::update(const sf::Vector2i& mousePosition) {

	this->buttonState = BTN_IDLE;

	if (this->button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition))) {
		this->buttonState = BTN_HOVER;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			this->buttonState = BTN_ACTIVE;
		}
	}
}

void Button::render(sf::RenderTarget& renderTarget) {
	renderTarget.draw(this->button);
}
