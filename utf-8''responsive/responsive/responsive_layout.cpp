//
// Created by twak on 07/10/2019.
//

#include "responsive_layout.h"
#include "responsive_label.h"
#include <iostream>

// you should probably make extensive changes to this function
void ResponsiveLayout::setGeometry(const QRect &r ) { // our layout should fit inside r

    QLayout::setGeometry(r);

    // for all the Widgets added in ResponsiveWindow.cpp
    for (int i = 0; i < list_.size(); i++) {

        QLayoutItem *o = list_.at(i);

        try {
            // cast the widget to one of our responsive labels
            ResponsiveLabel *label = static_cast<ResponsiveLabel *>(o->widget());

            if (label == NULL) // null: cast failed on pointer
                std::cout << "warning, unknown widget class in layout" << std::endl;
            else if (label -> text() == kNavTabs ) // headers go at the top
                label -> setGeometry(0+r.x(),0+r.y(),r.width(), 40);
            // only show a search button on small resolution, at the right of the window
            else if (label -> text() == kSButton && r.width() < 500)
                label -> setGeometry( r.width() - 65 + r.x(), 45+r.y(), 60, 40);
            // fixme: the focus-group did not like this behaviour for the search result element.
            else if (label -> text() == kSResultImage )
                label -> setGeometry( rand() % ( r.width ()-120 )    +r.x(),
                                      rand() % ( r.height()-100 ) +40+r.y(), 60, 60);
            else // otherwise: disappear label by moving out of bounds
                label -> setGeometry (-1,-1,0,0);

        }
        catch (std::bad_cast) {
            // bad_case: cast failed on reference...
            std::cout << "warning, unknown widget class in layout" << std::endl;
        }
    }
}

// following methods provide a trivial list-based implementation of the QLayout class
int ResponsiveLayout::count() const {

    return list_.size();
}

QLayoutItem *ResponsiveLayout::itemAt(int idx) const {

    return list_.value(idx);
}

QLayoutItem *ResponsiveLayout::takeAt(int idx) {

    return idx >= 0 && idx < list_.size() ? list_.takeAt(idx) : 0;
}

void ResponsiveLayout::addItem(QLayoutItem *item) {

    list_.append(item);
}

QSize ResponsiveLayout::sizeHint() const {

    return minimumSize();
}

QSize ResponsiveLayout::minimumSize() const {

    return QSize(320,320);
}

ResponsiveLayout::~ResponsiveLayout() {

    QLayoutItem *item;
    while ((item = takeAt(0)))
        delete item;
}
