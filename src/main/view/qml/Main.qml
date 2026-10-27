import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import QtMultimedia

ApplicationWindow {
    id: window
    visible: true
    visibility: "Maximized"
    width: 1000
    height: 700

    title: "Base de Datos Musical"

    Material.theme: Material.Dark
    Material.accent: Material.Indigo

    Text {
        anchors.centerIn: parent
        text: ".-."
        font.pixelSize: 24
    }

    header: ToolBar {
	id: buttonBar
	height: 50

	Boton {
	    width: 45
            height: 45
	    anchors.left: parent.left
	    anchors.leftMargin: 10
	    iconSource: "qrc:img/images/edit.png"
	    icon.color: "transparent"
	}

	Boton {
	    width: 45
            height: 45
	    anchors.right: parent.right
	    anchors.rightMargin: 10
	    iconSource: "qrc:img/images/pickaxe.png"
	    icon.color: "transparent"
	}
    }

    footer: ToolBar {
	id: mediaBar
	height: 60

	AudioOutput {
            id: musicOut
            volume: 1.0
	}

	MediaPlayer {
            id: player
            audioOutput: musicOut
            source: ""
	}

	Row {
            anchors.centerIn: parent
            spacing: 20

            Boton {
		id: musicButton
		height: 70
		iconSource: musicButton.playMusic ?
			"qrc:img/images/pause.png" : "qrc:img/images/play.png"

		property bool playMusic: false

		onClicked: {
		    playMusic = !playMusic
		    if (playMusic)
			player.play()
		    else
			player.pause()
		}
            }
	}
    }
}
