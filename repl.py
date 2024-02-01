import sys
import traceback

try:
    from py_animal import Dog, Cat, Elephant
except Exception as e:
    print("Failed to import animals", file=sys.stderr)
    traceback.print_exc()
    exit(1)

try:
    from py_world import Context, World
except Exception as e:
    traceback.print_exc()
    exit(1)


class REPL:
    _alive = True

    @classmethod
    def run_with_context(cls, context: Context, prompt: str = ">>> "):
        # readline utilities
        from rlcompleter import Completer
        import readline

        readline.parse_and_bind("tab: complete")
        readline.set_completer(Completer(locals()).complete)

        try:
        # use try-except to catch Ctrl+C as KeyboardInterrupt
            while cls._alive:
                _script = input(prompt)
                _compiled_expression = None
                _compiled_statement = None
                try:
                    _compiled_expression = compile(_script, '<string>', 'eval')
                except SyntaxError:
                    try:
                        _compiled_statement = compile(_script, '<string>','exec')
                    except SyntaxError:
                        print("Invalid syntax!")
                        continue
                except:
                    print("Invalid syntax!")
                    continue

                try:
                    if _compiled_expression is not None:
                        result = eval(_compiled_expression)
                        if result is not None:
                            print(result)
                    elif _compiled_statement is not None:
                        exec(_compiled_statement)
                except Exception as e:
                    traceback.print_exc()
        except (KeyboardInterrupt, SystemExit):
            print('\nREPL Exiting...')
            cls._alive = False


if __name__ == "__main__":
    REPL.run_with_world()
    print('Try to run again')
    REPL.run_with_world()


# current_world = context.current_world
# current_world.show_animals()

# dog = Dog()
# cat = Cat()
# elephant = Elephant()
# current_world.add_animal(dog)
# current_world.add_animal(cat)
# current_world.add_animal(elephant)

# current_world.show_animals()

# current_world.remove_animal(elephant)

# current_world.show_animals()