#include "gui_techlist.hpp"

TechListViewer::TechListViewer(std::vector<Techprocess> ptr)
{
    m_mainListLayout = new QVBoxLayout;
    m_techCombo = new QComboBox;
    m_techStack = new QStackedWidget;
    for (auto& techItem: ptr)
    {
        TechprocessViewer *techviewer = new TechprocessViewer(&techItem);
        m_techCombo->addItem(techItem.getName());
        m_techStack->addWidget(techviewer);
    }
    m_mainListLayout->addWidget(m_techCombo);
    m_mainListLayout->addWidget(m_techStack);
    setLayout(m_mainListLayout);
    connect(m_techCombo, QOverload<int>::of(&QComboBox::activated),
            m_techStack, &QStackedWidget::setCurrentIndex);
}

    
