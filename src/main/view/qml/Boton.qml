import QtQuick
import QtQuick.Controls.Material

Button {
    id: button
    width: 100
    height: 40

    contentItem: Text {
        text: button.text
        font: button.font
	color: button.Material.foreground
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }

    background: Rectangle {
	color: button.down ? "#444444" : (button.hovered ? "#333333" : button.Material.backgroundColor)
	border.color: (button.visualFocus || button.highlighted) ?
	    button.Material.accentColor : "#555555"
        border.width: (button.visualFocus || button.highlighted) ? 2 : 1
        radius: 4
    }
}
