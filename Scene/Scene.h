#ifndef SCENE_H
#define SCENE_H


class Scene {
private:
    int height{};
    int width{};

public:
    Scene();

    ~Scene();

    void initialiseScene();

    void printScene() const;

    [[nodiscard]] int getHeight() const;

    [[nodiscard]] int getWidth() const;
};


#endif //SCENE_H
