import QtQuick
import QtQuick.Controls.Material

Button {
    id: button
    width: 100
    height: 40

    property url iconSource: ""
    Material.accent: Material.BlueGrey
    highlighted: true

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
	    readonly property bool isSvg:
	    source.toString().toLowerCase().endsWith(".svg")

            visible: button.iconSource != ""
            source: button.iconSource
            fillMode: Image.PreserveAspectFit
            anchors.centerIn: parent
            width: parent.width * (isSvg ? 0.4 : 0.6)
            height: parent.height * (isSvg ? 0.4 : 0.6)
	    sourceSize.width: isSvg ? width : 0
	    sourceSize.height: isSvg ? height : 0
        }
    }
}
