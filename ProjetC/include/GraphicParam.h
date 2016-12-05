#ifndef GRAPHICPARAM_H
#define GRAPHICPARAM_H
#define GRASS 1
#define PATH 2
#define ROCK 3
#define SPRITE_AMOUNT 257
#define OBJECT_SPRITE_AMOUNT 402


class GraphicParam
{
    public:
        GraphicParam();
        GraphicParam(int graphicId);
        void    setGraphicId(int graphicId);
        int     getGraphicId();
    protected:
    private:
        int m_graphicId;
};

#endif // GRAPHICPARAM_H
