// Custom JavaScript for your website

// Function to show an alert when a button is clicked
function showAlert() {
    alert('Successfully Submit!');
}

// Add an event listener to a button with the ID "customButton"
document.addEventListener('DOMContentLoaded', function () {
    const customButton = document.querySelector('.submit');

    if (customButton) {
        customButton.addEventListener('click', showAlert);
    }
});
