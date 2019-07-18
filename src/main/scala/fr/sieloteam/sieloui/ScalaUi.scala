package fr.sieloteam.sieloui

import javafx.{collections => jfxc, concurrent => jfxr}

import scala.language.postfixOps
import scalafx.Includes._
import scalafx.application.JFXApp
import scalafx.collections.ObservableBuffer
import fr.sieloteam.sieloui.starter.Splash
import javafx.collections.ObservableList
import javafx.concurrent.Task

object ScalaUi extends JFXApp {
    val ApplicationIcon = "https://avatars1.githubusercontent.com/u/38626935?s=200&v=4"

    val moduleTask: Task[ObservableList[String]] = new jfxr.Task[jfxc.ObservableList[String]]() {
  
      protected def call: jfxc.ObservableList[String] = {
        val foundModules = new ObservableBuffer[String]()
        val availableModules = ObservableBuffer[String](
          "Core", "Historique", "Adblocker", "Téléchargement", "Cache", "Moteur de rendu")

        updateMessage("Finding other modules . . .")

        for (i <- availableModules.indices) {
          Thread.sleep(400)
          updateProgress(i + 1, availableModules.size)
          val nextModule = availableModules.get(i)
          foundModules += nextModule
          updateMessage("Finding modules . . . found " + nextModule)
        }
        Thread.sleep(400)
        updateMessage("All modules found.")
        foundModules
      }
    }
  
    Splash.show(new JFXApp.PrimaryStage(), moduleTask, () => showMainStage())
  
    new Thread(moduleTask).start()

    private def showMainStage(): Unit = {

    }
}