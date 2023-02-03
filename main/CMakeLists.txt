idf_component_register(SRCS "app_main.c" "board.c" "snake.c" "button.c" "ili9488.c"
                    REQUIRES driver
                    INCLUDE_DIRS "."
                    )
