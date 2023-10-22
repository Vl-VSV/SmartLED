from fastapi import APIRouter, HTTPException
from pydantic import Field

from routes.utitlity_functions import change_brightness, change_temperature, change_rainbow_step, change_speed, \
    change_animation_smooth, change_saturation

router = APIRouter()


@router.get('/increase/{value}')
def increase_value(value: str):
    """
    Increase the specified parameter value.

    **Args**:
        value (str): The parameter to increase.

        values:
        - temperature
        - speed
        - animation_smooth
        - rainbow_step
        - brightness
        - saturation

    **Returns**:
        dict: A JSON dictionary containing the updated parameter value.

    **Raises**:
        HTTPException: If the specified value is not supported.
    """
    if value == "temperature":
        return change_temperature("+")
    elif value == "speed":
        return change_speed("+")
    elif value == "animation_smooth":
        return change_animation_smooth("+")
    elif value == "rainbow_step":
        return change_rainbow_step("+")
    elif value == "brightness":
        return change_brightness("+")
    elif value == "saturation":
        return change_saturation("+")
    else:
        raise HTTPException(status_code=400, detail="Я пока этого не умею")


@router.get('/decrease/{value}')
def decrease_value(value: str):
    """
    Decrease the specified parameter value.

    **Args**:
        value (str): The parameter to increase.

        values:
        - temperature
        - speed
        - animation_smooth
        - rainbow_step
        - brightness
        - saturation

    **Returns**:
        dict: A JSON dictionary containing the updated parameter value.

    **Raises**:
        HTTPException: If the specified value is not supported.
    """
    if value == "temperature":
        return change_temperature("-")
    elif value == "speed":
        return change_speed("-")
    elif value == "animation_smooth":
        return change_animation_smooth("-")
    elif value == "rainbow_step":
        return change_rainbow_step("-")
    elif value == "brightness":
        return change_brightness("-")
    elif value == "saturation":
        return change_saturation("-")
    else:
        raise HTTPException(code=400, detail="Я пока этого не умею")


@router.get('/setMax/{value}')
def set_value_max(value: str):
    """
    Set the specified parameter value to max.

    **Args**:
        value (str): The parameter to increase.

        values:
        - temperature
        - speed
        - animation_smooth
        - rainbow_step
        - brightness
        - saturation

    **Returns**:
        dict: A JSON dictionary containing the updated parameter value.

    **Raises**:
        HTTPException: If the specified value is not supported.
    """
    if value == "temperature":
        return change_temperature("max")
    elif value == "speed":
        return change_speed("max")
    elif value == "animation_smooth":
        return change_animation_smooth("max")
    elif value == "rainbow_step":
        return change_rainbow_step("max")
    elif value == "brightness":
        return change_brightness("max")
    elif value == "saturation":
        return change_saturation("max")
    else:
        raise HTTPException(code=400, detail="Я пока этого не умею")


@router.get('/setMin/{value}')
def set_value_min(value: str):
    """
    Set the specified parameter value to min.

    **Args**:
        value (str): The parameter to increase.

        values:
        - temperature
        - speed
        - animation_smooth
        - rainbow_step
        - brightness
        - saturation

    **Returns**:
        dict: A JSON dictionary containing the updated parameter value.

    **Raises**:
        HTTPException: If the specified value is not supported.
    """
    if value == "temperature":
        return change_temperature("min")
    elif value == "speed":
        return change_speed("min")
    elif value == "animation_smooth":
        return change_animation_smooth("min")
    elif value == "rainbow_step":
        return change_rainbow_step("min")
    elif value == "brightness":
        return change_brightness("min")
    elif value == "saturation":
        return change_saturation("min")
    else:
        raise HTTPException(code=400, detail="Я пока этого не умею")
