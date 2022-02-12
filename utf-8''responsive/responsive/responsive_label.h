//
// Created by twak on 14/10/2019.
//

#ifndef RESPONSIVELABEL_H
#define RESPONSIVELABEL_H


#include <QLabel>
#include <QString>
#include <map>


// Please add to, but DO NOT modify the existing constants in this file.
// label names that are displayed

const QString
        kHomeLink       = "home", // see Lecture 7 for some terminology
        kShoppingBasket = "basket",
        kSignIn         = "sign-in",
        kMenu           = "...", //menu
        kNavTabs        = "navigation tabs",
        kAdvert         = "advert",
        kSButton        = "search",
        kSResultImage   = "image",
        kSResultText    = "description",
        kSQuery         = "search query",
        kSForward       = ">", // next page of search results
        kSBackward      = "<", // previous page of search results
        kSOptions       = "search options";

// every label name has a colour
const std::map<QString, QString> kColours = {
        std::make_pair(kHomeLink,       "#ffaaff"),
        std::make_pair(kShoppingBasket, "#ffaaaa"),
        std::make_pair(kSignIn,         "#aaffaa"),
        std::make_pair(kMenu,           "#cccccc"),
        std::make_pair(kNavTabs,        "#ffa9d3"),
        std::make_pair(kAdvert,         "#ffaa66"),
        std::make_pair(kSButton,        "#aaffff"),
        std::make_pair(kSResultImage,   "#99ddff"),
        std::make_pair(kSResultText,    "#77bbdd"),
        std::make_pair(kSQuery,         "#aaaaff"),
        std::make_pair(kSForward,       "#5caeff"),
        std::make_pair(kSBackward,      "#5caeff"),
        std::make_pair(kSOptions,       "#9dceff")
    };

class ResponsiveLabel : public QLabel {

public:
    ResponsiveLabel(QString name) ;
    ResponsiveLabel(QString name, QString colour) ;
};


#endif // RESPONSIVELABEL_H
