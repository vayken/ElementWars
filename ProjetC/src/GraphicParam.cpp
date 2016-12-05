#include "GraphicParam.h"

GraphicParam::GraphicParam()
{

}

GraphicParam::GraphicParam(int graphicId)
{
    this->m_graphicId = graphicId;
}

int GraphicParam::getGraphicId()
{
    return m_graphicId;
}

void GraphicParam::setGraphicId(int graphicId1){
    m_graphicId = graphicId1;
}

