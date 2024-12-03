# Ajout de la librairie en charge de compiler les SRC
add_library(gi_team_selector_library
    SRC_CPP/*.cpp)

target_include_directories(gi_team_selector_library PRIVATE INCLUDE)

