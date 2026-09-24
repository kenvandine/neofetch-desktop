*** Settings ***
Documentation    Test cases for neofetch-desktop snap
Resource         kvm.resource


*** Test Cases ***
Neofetch Desktop Launches And Renders
    [Documentation]    Verify neofetch-desktop snap launches and renders a UI on Mir
    [Tags]    smoke    yarf:certification_status: blocker
    Log Screenshot
