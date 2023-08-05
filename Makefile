SRCS		=		philo_control.c philo_utils.c philo_thread.c philo_division.c

OBJS		=		$(SRCS:.c=.o)

NAME		=		philo

CC			=		gcc

CFLAGS		=		-Wall -Wextra -Werror

RM			=		rm -rf

all:				$(NAME)

$(NAME):			$(OBJS)
						$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
					$(RM) $(OBJS)

fclean:				clean
						$(RM) $(NAME)

re:					fclean $(NAME)

.PHONY:				all clean fclean re