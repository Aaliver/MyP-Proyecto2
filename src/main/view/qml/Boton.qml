import QtQuick
import QtQuick.Controls.Material

Button {
    id: button
    width: 45
    height: 45

    icon.source: ""
    highlighted: true

    contentItem: Item {
        anchors.fill: parent

        Text {
            visible: button.icon.source == ""
            text: button.text
            font: button.font
            color: button.Material.foreground
            anchors.centerIn: parent
            elide: Text.ElideRight
        }

        Image {
            readonly property bool isSvg:
            source.toString().toLowerCase().endsWith(".svg")

            visible: button.icon.source != ""
            source: button.icon.source
            fillMode: Image.PreserveAspectFit
            anchors.centerIn: parent
            width: parent.width * (isSvg ? 0.4 : 0.6)
            height: parent.height * (isSvg ? 0.4 : 0.6)
            sourceSize.width: isSvg ? width : 0
            sourceSize.height: isSvg ? height : 0
        }
    }
}
