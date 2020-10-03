//<1번 Door 클래스 선언>

#include <Object.h>

class Door : public bangtal::Object
{
public:
	static bangtal::ObjectPtr create(const std::string& openedImage, bangtal::ScenePtr locatedScene = nullptr, int x = 0, int y = 0,
		bangtal::ScenePtr connectedScene = nullptr, bool closed = false, const std::string& closedImage = "", bool shown = true) {
		auto object = ObjectPtr(new Door(openedImage, locatedScene, x, y, connectedScene, closed, closedImage, shown));
		Object::add(object);

		return object;
	}

protected:
	Door(const std::string& openedImage, bangtal::ScenePtr locatedScene, int x, int y, bangtal::ScenePtr connectedScene, bool closed, const std::string& closedImage, bool shown) : bangtal::Object(closed ? closedImage : openedImage, locatedScene, x, y, shown), _connectedScene(connectedScene), _closed(closed), _closedImage(closedImage), _openedImage(openedImage){}

public:
	virtual bool onMouse(int x, int y, MouseAction action) {
		if (!Object::onMouse(x, y, action)) {
			if (_closed) {
				if (!_openedImage.empty())
					setImage(_openedImage);
				_closed = false;
			}
			else {
				if (_connectedScene)
					_connectedScene->enter();
				else endGame();
			}
		}

		return true;
	}

protected:
	bool _closed;
	std::string _closedImage, _openedImage;
	bangtal::ScenePtr _connectedScene;
};


//<2번 클래스 선언>



class LockedDoor : public Door
{
public:
	static bangtal::ObjectPtr create(const std::string& openedImage, bangtal::ScenePtr locatedScene = nullptr, int x = 0, int y = 0,
		bangtal::ScenePtr connectedScene = nullptr, bool closed = false, const std::string& closedImage = "", bool shown = true, bool locked) {
		auto object = ObjectPtr(new Door(openedImage, locatedScene, x, y, connectedScene, closed, closedImage, shown));
		Object::add(object);

		return object;
	}

protected:
	Door(const std::string& openedImage, bangtal::ScenePtr locatedScene, int x, int y, bangtal::ScenePtr connectedScene, bool closed, const std::string& closedImage, bool shown) : bangtal::Object(closed ? closedImage : openedImage, locatedScene, x, y, shown), _connectedScene(connectedScene), _closed(closed), _closedImage(closedImage), _openedImage(openedImage), _locked(locked) {}

public:
	virtual bool onMouse(int x, int y, MouseAction action) {
		if (!Object::onMouse(x, y, action)) {
			if (_closed) {
				if (!_openedImage.empty())
					setImage(_openedImage);
				_closed = false;
			}
			else {
				if (_connectedScene)
					_connectedScene->enter();
				else endGame();
			}
		}

		return true;
	}

protected:
	bool _closed;
	bool _locked;
	std::string _closedImage, _openedImage;
	bangtal::ScenePtr _connectedScene;
};
