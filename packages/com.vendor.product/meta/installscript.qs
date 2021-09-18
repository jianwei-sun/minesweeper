function Component()
{
    // default constructor
}

Component.prototype.createOperations = function()
{
    // This actually installs the files
    component.createOperations();

    if (systemInfo.productType == "windows") {
        // Start menu shortcut
        component.addOperation("CreateShortcut", 
                               "@TargetDir@/Minesweeper.exe", 
                               "@StartMenuDir@/Minesweeper.lnk", 
                               "workingDirectory=@TargetDir@", 
                               "iconPath=@TargetDir@/Minesweeper.exe", "iconId=0");

       // Desktop Shortcut
       component.addOperation("CreateShortcut", 
                              "@TargetDir@/Minesweeper.exe",
                              "@DesktopDir@/Minesweeper.lnk",
                              "workingDirectory=@TargetDir@", 
                              "iconPath=@TargetDir@/Minesweeper.exe", "iconId=0");
    }
}