#include <SFML/Graphics.hpp>
#include <iostream>

enum button_states { BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE };

class Button {
private:
	short unsigned buttonState;

	sf::Sprite button;
	sf::Texture button_t;


public:
	Button(sf::Texture* texture, sf::Vector2f position = sf::Vector2f());
	~Button();


	//	MODIFIERS
	void setPosition(sf::Vector2f position, bool fromCenter = false);
	void setScale(float, float);

	//	ACCESSORS
	const bool isPressed() const;
	const sf::FloatRect getGlobalBounds() const;

	//	FUNCTIONS
	void update(const sf::Vector2i& mousePosition);
	void render(sf::RenderTarget& renderTarget);
};