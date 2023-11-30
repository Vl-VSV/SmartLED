# Dockerfile
FROM python:3.9

WORKDIR /code

# Copy requirements
COPY ./requirements.txt /code/requirements.txt

# Install requirements
RUN pip install --no-cache-dir --upgrade -r /code/requirements.txt

# Copy files
COPY ./main.py /code
COPY ./data_model.py /code
COPY ./routes /code/routes

# Run
CMD python main.py
