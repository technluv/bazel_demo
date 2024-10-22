# Build stage
FROM gcc:latest as cpp-builder
WORKDIR /app
COPY src/core /app/core
RUN g++ -shared -fPIC -o libprocessor.so core/lib/processor.cpp -Icore/include

# Python stage
FROM python:3.9-slim
WORKDIR /app
COPY requirements.txt .
RUN pip install --no-cache-dir -r requirements.txt
COPY src/services /app/services
COPY --from=cpp-builder /app/libprocessor.so /app/

ENV PYTHONPATH=/app
CMD ["uvicorn", "services.processor_service:app", "--host", "0.0.0.0", "--port", "8000"]
