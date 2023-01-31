idf_component_register(SRCS "app_main.c" "board.c" "snake.c" "button.c"
                    REQUIRES driver
                    INCLUDE_DIRS "."
                    )
