import QtQuick
import QtQuick.Controls.Material

Button {
    id: button
    width: 100
    height: 40

    property url iconSource: ""

    contentItem: Item {
	anchors.fill: parent

	Text {
	    visible: button.iconSource == ""
            text: button.text
            font: button.font
	    color: button.Material.foreground
	    anchors.centerIn: parent
            elide: Text.ElideRight
	}

	Image {
            visible: button.iconSource != ""
            source: button.iconSource
            fillMode: Image.PreserveAspectFit
            anchors.centerIn: parent
            width: parent.height * 0.6
            height: parent.height * 0.6
        }
    }

    background: Rectangle {
	color: button.down ? "#444444" :
	    (button.hovered ? "#333333" : button.Material.backgroundColor)
	border.color: (button.visualFocus || button.highlighted) ?
	    button.Material.accentColor : "#555555"
        border.width: (button.visualFocus || button.highlighted) ? 2 : 1
        radius: 4
    }
}
