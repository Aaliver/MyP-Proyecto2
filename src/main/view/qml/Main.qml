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
	    iconSource: "qrc:/img/images/edit.png"
	    icon.color: "transparent"
	}

	Boton {
	    width: 45
            height: 45
	    anchors.right: parent.right
	    anchors.rightMargin: 10
	    iconSource: "qrc:/img/images/pickaxe.png"
	    icon.color: "transparent"
	}
    }

    footer: ToolBar {
	id: mediaBar
	height: 60

	AudioOutput {
            id: musicOutput
            volume: volumeSlider.value
	}

	MediaPlayer {
            id: player
            audioOutput: musicOutput
            source: ""

	    function time(ms) {
		if (ms <= 0 || isNaN(ms))
		    return "00:00"
		var totalSeconds = Math.floor(ms / 1000)
		var minutes = Math.floor(totalSeconds / 60)
		var seconds = totalSeconds % 60
		return (minutes < 10 ? "0" : "") + minutes + ":" +
		    (seconds < 10 ? "0" : "") + seconds
	    }
	}

	Item {
	    width: window.width / 3.5
	    height: parent.height
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.verticalCenter: parent.verticalCenter

	    Label {
		id: currentMusicTime
                text: player.time(player.position)
		anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
            }

	    Item {
		anchors.left: currentMusicTime.right
                anchors.right: totalMusicTime.left
                anchors.leftMargin: 15
                anchors.rightMargin: 15
                height: 40
                anchors.verticalCenter: parent.verticalCenter
                Material.accent: Material.Grey

                Slider {
                    anchors.fill: parent
                    from: 0
                    to: player.duration
                    value: player.position
                    onMoved: player.position = value
                }
            }

            Label {
		id: totalMusicTime
                text: player.time(player.duration)
		anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        Boton {
	    id: musicButton
	    height: 70
	    anchors.centerIn: parent
	    iconSource: musicButton.playMusic ?
		"qrc:/img/images/pause.png" : "qrc:/img/images/play.png"
	    background: null

	    property bool playMusic: false

	    onClicked: {
		playMusic = !playMusic
		if (playMusic)
		    player.play()
		else
		    player.pause()
	    }
        }

	Item {
	    width: window.width / 6
	    height: parent.height
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.verticalCenter: parent.verticalCenter

	    Image {
		id: volumeIcon
		sourceSize.height: 20
		sourceSize.width: 20
		anchors.left: parent.left
		source: {
		    if (volume === 0.0)
			return "qrc:/img/images/volume-mute.svg";
		    if (volume === 1.0)
			return "qrc:/img/images/volume-high.svg";
		    return "qrc:/img/images/volume-low.svg";
		}
		fillMode: Image.PreserveAspectFit
		anchors.verticalCenter: parent.verticalCenter

		property real volume: volumeSlider.value
	    }

	    Item {
		anchors.left: volumeIcon.right
                anchors.right: parent.right
                anchors.leftMargin: 15
                height: 40
                anchors.verticalCenter: parent.verticalCenter
                Material.accent: Material.Grey

                Slider {
		    id: volumeSlider
                    anchors.fill: parent
                    from: 0.0
                    to: 1.0
		    value: 0.75
		    stepSize: 0.05
		    live: true
                }
            }
	}
    }
}
